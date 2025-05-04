  const API_URL = 'http://localhost:3000/api/tasks';

  document.addEventListener('DOMContentLoaded', loadTasks);

  function loadTasks() {
    const xhr = new XMLHttpRequest();
    xhr.open('GET', API_URL);
    xhr.onload = function () {
      if (xhr.status === 200) {
        const tasks = JSON.parse(xhr.responseText);
        document.getElementById('task-list').innerHTML = '';
        tasks.forEach(addTaskToDOM);
      }
    };
    xhr.send();
  }

  function addTask() {
    const input = document.getElementById('new-task');
    const text = input.value.trim();
    if (!text) return;

    const xhr = new XMLHttpRequest();
    xhr.open('POST', API_URL);
    xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8');
    xhr.onload = function () {
      if (xhr.status === 200 || xhr.status === 201) {
        const task = JSON.parse(xhr.responseText);
        addTaskToDOM(task);
        input.value = '';
      }
    };
    xhr.send(JSON.stringify({ text, completed: false }));
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
    const xhr = new XMLHttpRequest();
    xhr.open('PUT', `${API_URL}/${id}`);
    xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8');
    xhr.onload = function () {
      if (xhr.status === 200) {
        loadTasks();
      }
    };
    xhr.send(JSON.stringify({ completed }));
  }

  function deleteTask(id) {
    const xhr = new XMLHttpRequest();
    xhr.open('DELETE', `${API_URL}/${id}`);
    xhr.onload = function () {
      if (xhr.status === 200) {
        loadTasks();
      }
    };
    xhr.send();
  }
