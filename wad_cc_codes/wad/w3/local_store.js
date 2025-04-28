document.addEventListener("DOMContentLoaded", () => {
    const form = document.getElementById("registrationForm");
    const resetBtn = document.getElementById("resetBtn");
    const userList = document.getElementById("userList");
  
    // Load users from localStorage on page load
    const users = JSON.parse(localStorage.getItem("users")) || [];
    users.forEach(displayUser);
  
    form.addEventListener("submit", function (event) {
      event.preventDefault();
  
      const name = document.getElementById("name").value;
      const email = document.getElementById("email").value;
      const username = document.getElementById("username").value;
  
      const userData = { name, email, username };
      users.push(userData);
      localStorage.setItem("users", JSON.stringify(users));
  
      displayUser(userData);
      form.reset();
    });
  
    resetBtn.addEventListener("click", () => {
      form.reset();
    });
  
    function displayUser(user) {
      const card = document.createElement("div");
      card.className = "user-card";
      card.innerHTML = `
        <strong>Name:</strong> ${user.name}<br>
        <strong>Email:</strong> ${user.email}<br>
        <strong>Username:</strong> ${user.username}
      `;
      userList.appendChild(card);
    }
  });
  