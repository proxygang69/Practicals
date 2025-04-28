const express = require('express');
const path = require('path');
const fs = require('fs');
const app = express();

// Serve static files (HTML, CSS, images)
app.use(express.static(path.join(__dirname, 'public')));

// API to get employee data
app.get('/api/employees', (req, res) => {
  fs.readFile('employees.json', 'utf8', (err, data) => {
    if (err) {
      return res.status(500).send('Error reading employee data.');
    }
    res.json(JSON.parse(data));
  });
});

// Start server
const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server is running at http://localhost:${PORT}`);
});
