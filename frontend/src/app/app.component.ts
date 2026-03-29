import { Component, HostListener } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-root',
  imports: [FormsModule],
  templateUrl: './app.component.html',
  styleUrl: './app.component.scss'
})
export class AppComponent {
  title = 'Portfolio';
  navOpen = false;
  contactStatus: 'idle' | 'sending' | 'ok' | 'error' = 'idle';

  contact = {
    name: '',
    email: '',
    message: ''
  };

  readonly projects = [
    {
      name: 'API platform',
      stack: 'Django · PostgreSQL',
      blurb: 'REST services with clear contracts and predictable deployments.'
    },
    {
      name: 'Client dashboard',
      stack: 'Angular · TypeScript',
      blurb: 'Focused UI for monitoring metrics with fast, accessible layouts.'
    },
    {
      name: 'Automation toolkit',
      stack: 'Python · CI',
      blurb: 'Scripts and pipelines that keep releases boring—in a good way.'
    }
  ];

  constructor(private readonly http: HttpClient) {}

  @HostListener('window:keydown.escape')
  onEscape(): void {
    this.navOpen = false;
  }

  scrollTo(id: string): void {
    this.navOpen = false;
    const el = document.getElementById(id);
    el?.scrollIntoView({ behavior: 'smooth', block: 'start' });
  }

  submitContact(): void {
    if (this.contactStatus === 'sending') {
      return;
    }
    this.contactStatus = 'sending';
    this.http.post<{ ok: boolean }>('/api/contact/', this.contact).subscribe({
      next: (res) => {
        if (res.ok) {
          this.contactStatus = 'ok';
          this.contact = { name: '', email: '', message: '' };
        } else {
          this.contactStatus = 'error';
        }
      },
      error: () => {
        this.contactStatus = 'error';
      }
    });
  }
}
