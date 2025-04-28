import { Component, OnInit } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css',
})
export class AppComponent implements OnInit {
  newTask: string = '';
  tasks: string[] = [];
  editIndex: number | null = null;

  ngOnInit() {
    if (typeof window !== 'undefined' && localStorage) {
      const storedTasks = localStorage.getItem('tasks');
      if (storedTasks) {
        this.tasks = JSON.parse(storedTasks);
      }
    }
  }

  saveTasks() {
    if (typeof window !== 'undefined' && localStorage) {
      localStorage.setItem('tasks', JSON.stringify(this.tasks));
    }
  }

  addTask() {
    if (this.newTask.trim() !== '') {
      this.tasks.push(this.newTask.trim());
      this.saveTasks();
      this.newTask = '';
    }
  }

  editTask(index: number) {
    this.newTask = this.tasks[index];
    this.editIndex = index;
  }

  updateTask() {
    if (this.editIndex !== null && this.newTask.trim() !== '') {
      this.tasks[this.editIndex] = this.newTask.trim();
      this.saveTasks();
      this.editIndex = null;
      this.newTask = '';
    }
  }

  deleteTask(index: number) {
    this.tasks.splice(index, 1);
    this.saveTasks();
    if (this.editIndex === index) {
      this.editIndex = null;
      this.newTask = '';
    }
  }
}
