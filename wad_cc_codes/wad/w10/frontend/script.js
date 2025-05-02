const API_URL = 'http://localhost:3000/api/tasks';

document.addEventListener('DOMContentLoaded', loadTasks);

function loadTasks() {
  fetch(API_URL)
    .then(res => res.json())
    .then(tasks => {
      document.getElementById('task-list').innerHTML = '';
      tasks.forEach(addTaskToDOM);
    });
}

function addTask() {
  const input = document.getElementById('new-task');
  const text = input.value.trim();
  if (!text) return;

  fetch(API_URL, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ text, completed: false })
  })
    .then(res => res.json())
    .then(task => {
      addTaskToDOM(task);
      input.value = '';
    });
}

function addTaskToDOM(task) {
  const li = document.createElement('li');
  li.innerHTML = `
    <span class="${task.completed ? 'done' : ''}" onclick="toggleTask(${task.id}, ${!task.completed})">${task.text}</span>
    <button onclick="deleteTask(${task.id})">❌</button>
  `;
  document.getElementById('task-list').appendChild(li);
}

function toggleTask(id, completed) {
  fetch(`${API_URL}/${id}`, {
    method: 'PUT',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ completed })
  }).then(() => loadTasks());
}

function deleteTask(id) {
  fetch(`${API_URL}/${id}`, { method: 'DELETE' }).then(() => loadTasks());
}
