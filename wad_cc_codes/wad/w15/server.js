const express = require('express');
const app = express();
const fs = require('fs');
const path = require('path');

// Middleware to serve static files
app.use(express.static('public'));

// API endpoint to get product data
app.get('/api/products', (req, res) => {
  fs.readFile(path.join(__dirname, 'products.json'), 'utf8', (err, data) => {
    if (err) {
      res.status(500).send('Error reading product data');
    } else {
      res.json(JSON.parse(data));
    }
  });
});

// Start server
const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
