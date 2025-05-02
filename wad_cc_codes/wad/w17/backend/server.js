const express = require('express');
const cors = require('cors');
const fs = require('fs');
const app = express();

app.use(cors());

app.get('/api/employees', (req, res) => {
  fs.readFile(__dirname + '/employees.json', 'utf8', (err, data) => {
    if (err) return res.status(500).json({ error: 'Failed to read data' });

    try {
      const employees = JSON.parse(data);
      res.json(employees);
    } catch (parseErr) {
      res.status(500).json({ error: 'Invalid JSON format' });
    }
  });
});


const PORT = 3000;
app.listen(PORT, () => console.log(`Server running on http://localhost:${PORT}`));
