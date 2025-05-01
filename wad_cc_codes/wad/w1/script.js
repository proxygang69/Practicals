const products = [
    {
      name: "Wireless Headphones",
      price: "₹7,999",
      desc: "Noise-cancelling over-ear headphones.",
      image: "images/headphones.jpg",
    },
    {
      name: "Smartwatch",
      price: "₹12,999",
      desc: "Fitness tracking smartwatch.",
      image: "images/smartwatch.jpg",
    },
    {
      name: "Gaming Mouse",
      price: "₹2,499",
      desc: "Ergonomic gaming mouse.",
      image: "images/mouse.jpg",
    },
    {
      name: "Laptop Stand",
      price: "₹1,999",
      desc: "Adjustable aluminium stand.",
      image: "images/laptop-stand.jpg",
    },
    // Add more objects for testing pagination
  ];
  
  const rowsPerPage = 2;
  let currentPage = 1;
  
  function displayProducts() {
    const start = (currentPage - 1) * rowsPerPage;
    const end = start + rowsPerPage;
    const paginatedItems = products.slice(start, end);
  
    const tbody = document.getElementById("product-table-body");
    tbody.innerHTML = "";
  
    paginatedItems.forEach(p => {
      const row = `<tr>
        <td><img src="${p.image}" alt="${p.name}"></td>
        <td>${p.name}</td>
        <td>${p.price}</td>
        <td>${p.desc}</td>
      </tr>`;
      tbody.innerHTML += row;
    });
  
    document.getElementById("page-info").textContent = `Page ${currentPage} of ${Math.ceil(products.length / rowsPerPage)}`;
  }
  
  document.getElementById("prev").addEventListener("click", () => {
    if (currentPage > 1) {
      currentPage--;
      displayProducts();
    }
  });
  
  document.getElementById("next").addEventListener("click", () => {
    if (currentPage < Math.ceil(products.length / rowsPerPage)) {
      currentPage++;
      displayProducts();
    }
  });
  
  displayProducts();
  