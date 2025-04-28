const express = require('express');
const cors = require('cors');
const fs = require('fs');
const path = require('path');

const app = express();
const PORT = 3000;

// Enable CORS
app.use(cors());

// Serve static files from 'public' folder
app.use(express.static('public'));

// API route to get users
app.get('/api/users', (req, res) => {
  const filePath = path.join(__dirname, 'users.json');
  fs.readFile(filePath, 'utf8', (err, data) => {
    if (err) {
      return res.status(500).json({ message: 'Error reading user data' });
    }
    const users = JSON.parse(data);
    res.json(users);
  });
});

// Start server
app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
