fetch('http://localhost:3000/api/products')
  .then(res => res.json())
  .then(products => {
    const container = document.getElementById('productList');
    products.forEach(product => {
      const card = document.createElement('div');
      card.className = 'product-card';
      card.innerHTML = `
        <img src="${product.image}" alt="${product.name}">
        <h2>${product.name}</h2>
        <p>$${product.price.toFixed(2)}</p>
      `;
      container.appendChild(card);
    });
  })
  .catch(error => console.error('Failed to load products:', error));
