import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { RouterModule, Router } from '@angular/router';
import { AuthService } from '../../services/auth.service';
import { User } from '../../models/user';

@Component({
  selector: 'app-register',
  standalone: true,
  imports: [CommonModule, FormsModule, RouterModule],
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent {
  user: User = { name: '', email: '', password: '' };

  constructor(private authService: AuthService, private router: Router) {}

  register(): void {
    this.authService.register(this.user);
    alert('Registered successfully!');
    this.router.navigate(['/']);
  }

  resetForm(): void {
    this.user = { name: '', email: '', password: '' };
  }
}
