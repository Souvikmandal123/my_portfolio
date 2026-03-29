import mimetypes
from pathlib import Path

from django.http import FileResponse, Http404

DIST_DIR = Path(__file__).resolve().parent.parent.parent / "web"


def _safe_file(dist: Path, rel_path: str) -> Path | None:
    if not rel_path:
        return None
    candidate = (dist / rel_path).resolve()
    try:
        candidate.relative_to(dist.resolve())
    except ValueError:
        return None
    return candidate if candidate.is_file() else None


def spa_serve(request, path: str = ""):
    """Serve static files from web/; fall back to index.html."""
    if path:
        file_path = _safe_file(DIST_DIR, path)
        if file_path:
            content_type = mimetypes.guess_type(str(file_path))[0] or "application/octet-stream"
            return FileResponse(open(file_path, "rb"), content_type=content_type)
    index = DIST_DIR / "index.html"
    if index.is_file():
        return FileResponse(open(index, "rb"), content_type="text/html; charset=utf-8")
    raise Http404("Static site not found. Ensure the web/ folder exists with index.html.")
