const express = require('express');
const fs = require('fs');
const path = require('path');
const cors = require('cors');
const bodyParser = require('body-parser');

const app = express();
const PORT = 3000;
const DATA_FILE = path.join(__dirname, 'tasks.json');

app.use(cors());
app.use(bodyParser.json());

// Read tasks
app.get('/api/tasks', (req, res) => {
  fs.readFile(DATA_FILE, 'utf8', (err, data) => {
    if (err) return res.status(500).json({ error: 'Failed to read tasks.' });
    res.json(JSON.parse(data || '[]'));
  });
});

// Add task
app.post('/api/tasks', (req, res) => {
  const newTask = req.body;
  fs.readFile(DATA_FILE, 'utf8', (err, data) => {
    let tasks = data ? JSON.parse(data) : [];
    newTask.id = Date.now();
    tasks.push(newTask);
    fs.writeFile(DATA_FILE, JSON.stringify(tasks), () => {
      res.json(newTask);
    });
  });
});

// Update task
app.put('/api/tasks/:id', (req, res) => {
  const taskId = parseInt(req.params.id);
  const updatedTask = req.body;
  fs.readFile(DATA_FILE, 'utf8', (err, data) => {
    let tasks = JSON.parse(data || '[]');
    tasks = tasks.map(task => (task.id === taskId ? { ...task, ...updatedTask } : task));
    fs.writeFile(DATA_FILE, JSON.stringify(tasks), () => {
      res.json(updatedTask);
    });
  });
});

// Delete task
app.delete('/api/tasks/:id', (req, res) => {
  const taskId = parseInt(req.params.id);
  fs.readFile(DATA_FILE, 'utf8', (err, data) => {
    let tasks = JSON.parse(data || '[]');
    tasks = tasks.filter(task => task.id !== taskId);
    fs.writeFile(DATA_FILE, JSON.stringify(tasks), () => {
      res.json({ id: taskId });
    });
  });
});

app.listen(PORT, () => console.log(`Server running on http://localhost:${PORT}`));
