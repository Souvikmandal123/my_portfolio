import json

from django.conf import settings
from django.core.exceptions import ValidationError
from django.core.mail import EmailMessage
from django.core.validators import validate_email
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from django.views.decorators.http import require_POST

MESSAGE_MAX_LEN = 5000


def _smtp_configured() -> bool:
    return bool(
        settings.CONTACT_TO_EMAIL
        and settings.EMAIL_HOST_USER
        and settings.EMAIL_HOST_PASSWORD
        and settings.EMAIL_HOST
    )


@csrf_exempt
@require_POST
def contact(request):
    if not _smtp_configured():
        return JsonResponse(
            {
                "ok": False,
                "error": "Email is not configured on the server. Set CONTACT_TO_EMAIL and SMTP variables.",
            },
            status=503,
        )

    try:
        data = json.loads(request.body.decode("utf-8"))
    except (json.JSONDecodeError, UnicodeDecodeError):
        return JsonResponse({"ok": False, "error": "Invalid JSON"}, status=400)

    name = (data.get("name") or "").strip()
    email = (data.get("email") or "").strip()
    message = (data.get("message") or "").strip()

    if not name or not email or not message:
        return JsonResponse({"ok": False, "error": "All fields are required"}, status=400)

    if len(message) > MESSAGE_MAX_LEN:
        return JsonResponse({"ok": False, "error": "Message is too long"}, status=400)

    try:
        validate_email(email)
    except ValidationError:
        return JsonResponse({"ok": False, "error": "Invalid email address"}, status=400)

    subject = f"[Portfolio] Message from {name}"
    body = (
        f"You received a message via the portfolio contact form.\n\n"
        f"Name: {name}\n"
        f"Email: {email}\n\n"
        f"Message:\n{message}\n"
    )

    mail = EmailMessage(
        subject=subject,
        body=body,
        from_email=settings.DEFAULT_FROM_EMAIL,
        to=[settings.CONTACT_TO_EMAIL],
        reply_to=[email],
    )

    try:
        mail.send(fail_silently=False)
    except Exception:
        return JsonResponse(
            {"ok": False, "error": "Could not send email. Check SMTP settings and try again later."},
            status=502,
        )

    return JsonResponse({"ok": True})
