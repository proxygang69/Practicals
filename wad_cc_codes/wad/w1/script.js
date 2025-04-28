document.addEventListener("DOMContentLoaded", () => {
    let currentPage = 1;
    const limit = 10;  // Items per page

    // Function to fetch products for a given page
    function fetchProducts(page) {
        fetch(`http://localhost:5000/api/products?page=${page}&limit=${limit}`)
            .then(response => response.json())
            .then(data => {
                const productList = document.getElementById("product-list");
                productList.innerHTML = ""; // Clear current products

                data.products.forEach(product => {
                    const productDiv = document.createElement("div");
                    productDiv.classList.add("product");

                    productDiv.innerHTML = `
                        <img src="${product.image}" alt="${product.name}">
                        <h2>${product.name}</h2>
                        <p>$${product.price.toFixed(2)}</p>
                        <button>${product.description}</button>
                    `;

                    productList.appendChild(productDiv);
                });

                // Update pagination controls
                updatePagination(data.currentPage, data.totalPages);
            })
            .catch(error => console.error("Error fetching products:", error));
    }

    // Function to update pagination controls
    function updatePagination(currentPage, totalPages) {
        const pagination = document.getElementById("pagination");
        pagination.innerHTML = "";  // Clear existing pagination controls

        // Add "Previous" button
        if (currentPage > 1) {
            const prevBtn = document.createElement("button");
            prevBtn.textContent = "Previous";
            prevBtn.onclick = () => {
                currentPage--;
                fetchProducts(currentPage);
            };
            pagination.appendChild(prevBtn);
        }

        // Add page numbers
        for (let i = 1; i <= totalPages; i++) {
            const pageBtn = document.createElement("button");
            pageBtn.textContent = i;
            pageBtn.onclick = () => {
                currentPage = i;
                fetchProducts(currentPage);
            };
            if (i === currentPage) {
                pageBtn.style.fontWeight = "bold"; // Highlight current page
            }
            pagination.appendChild(pageBtn);
        }

        // Add "Next" button
        if (currentPage < totalPages) {
            const nextBtn = document.createElement("button");
            nextBtn.textContent = "Next";
            nextBtn.onclick = () => {
                currentPage++;
                fetchProducts(currentPage);
            };
            pagination.appendChild(nextBtn);
        }
    }

    // Fetch the first page of products on load
    fetchProducts(currentPage);
});
