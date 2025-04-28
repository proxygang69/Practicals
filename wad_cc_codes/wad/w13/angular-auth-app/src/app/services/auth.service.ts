import { Injectable } from '@angular/core';
import { User } from '../models/user';

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  private localKey = 'users';
  private currentKey = 'currentUser';

  register(user: User): void {
    const users = this.getAllUsers();
    users.push(user);
    localStorage.setItem(this.localKey, JSON.stringify(users));
  }

  login(email: string, password: string): boolean {
    const users = this.getAllUsers();
    const user = users.find(u => u.email === email && u.password === password);
    if (user) {
      localStorage.setItem(this.currentKey, JSON.stringify(user));
      return true;
    }
    return false;
  }

  getAllUsers(): User[] {
    return JSON.parse(localStorage.getItem(this.localKey) || '[]');
  }

  getCurrentUser(): User | null {
    const user = localStorage.getItem(this.currentKey);
    return user ? JSON.parse(user) : null;
  }

  logout(): void {
    localStorage.removeItem(this.currentKey);
  }
}
