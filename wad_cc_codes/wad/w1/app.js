const express = require("express");
const cors = require("cors");
const fs = require("fs");

const app = express();
const PORT = 5000;

app.use(cors());

// Route to get product data with pagination
app.get("/api/products", (req, res) => {
    // Get page and limit parameters from query string (defaults to page 1 and 10 items per page)
    const page = parseInt(req.query.page) || 1;
    const limit = parseInt(req.query.limit) || 10;
    const startIndex = (page - 1) * limit;

    fs.readFile("products.json", "utf8", (err, data) => {
        if (err) {
            return res.status(500).json({ error: "Failed to read product data" });
        }

        const products = JSON.parse(data);
        const paginatedProducts = products.slice(startIndex, startIndex + limit);
        
        res.json({
            total: products.length,
            products: paginatedProducts,
            currentPage: page,
            totalPages: Math.ceil(products.length / limit)
        });
    });
});

app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
