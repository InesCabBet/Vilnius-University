const library = [
  {
    title: "Pinocho",
    author: "Carlo Collodi",
    pages: 120,
    image: "https://wmagazin.com/wp-content/uploads/2024/12/Portadas.2024-mejores-bonitas-pinocho-collodi-WMagazin-e1735465749152.jpg",
    read: false
  },
  {
    title: "Historias de Terror",
    author: "Maria Perez",
    pages: 345,
    image: "https://marketplace.canva.com/EAG0XmGvn1Q/2/0/1003w/canva-portada-para-libro-de-terror-texturizado-rojo-KZUPFETTvAo.jpg",
    read: false
  },
  {
    title: "Sapiens",
    author: "Yuval Noah",
    pages: 210,
    image: "https://thumb.knygos-static.lt/lwR-YGTaLQz-rf0c-csYcHurP9Q=/fit-in/0x801/images/books/1166468/41mjx6yzfel--sx324-bo1-204-203-200-.jpg",
    read: false
  },{
    title: "Harry Potter",
    author: "JK Rowling",
    pages: 408,
    image: "https://m.media-amazon.com/images/S/compressed.photo.goodreads.com/books/1627042661i/58613224.jpg",
    read: false
  },
  {
    title: "to kill a mockingbird",
    author: "Harper Lee",
    pages: 293,
    image: "https://m.media-amazon.com/images/I/81aY1lxk+9L._AC_UF1000,1000_QL80_.jpg",
    read: true
  },
  {
    title: "Le petit prince",
    author: "Antoine de Saint-Exupéry",
    pages: 50,
    image: "https://m.media-amazon.com/images/I/71IF1ngy57L._AC_UF1000,1000_QL80_.jpg",
    read: true
  },
  {
    title: "Divergent",
    author: "Veronica Roth",
    pages: 516,
    image: "https://online.fliphtml5.com/jiqdt/peqd/files/large/1.webp?1605597096&1605597096",
    read: true
  }
];

document.addEventListener("DOMContentLoaded", () => {
  const layout = document.querySelector(".layout");
  const form = document.querySelector(".book-form");
  const newBookButton = document.querySelector(".new-book");
  const cancelButton = document.getElementById("cancel");
  const modal = document.querySelector(".modal") || null; // solo si usas popup modal

  //Render inicial desde el array library
  function renderLibrary() {
    layout.innerHTML = ""; // limpia por si acaso
    library.forEach((book) => addBookToLayout(book));
  }

  // Crea una tarjeta de libro
  function addBookToLayout(book) {
    const bookCard = document.createElement("div");
    bookCard.classList.add("book");
    bookCard.innerHTML = `
      <img src="${book.image}" alt="${book.title}"/>
      <p class="book-title">${book.title}</p>
      <p class="book-author">${book.author}</p>
      <p class="book-pages">${book.pages}</p>
      <button class="book-status ${book.read ? "read" : ""}">
        ${book.read ? "Read" : "Unread"}
      </button>
      <button class="delete">Delete</button>`;
    layout.appendChild(bookCard);
  }

  //Mostrar / ocultar formulario o modal
  newBookButton.addEventListener("click", () => {
    if (modal) {
      modal.style.display = "flex";
    } else {
      form.style.display = form.style.display === "flex" ? "none" : "flex";
    }
  });

  //Botón cancelar
  cancelButton.addEventListener("click", () => {
    form.reset();
    if (modal) modal.style.display = "none";
    else form.style.display = "none";
  });

  //Enviar formulario
  form.addEventListener("submit", (event) => {
    event.preventDefault();
    const newBook = {
      title: document.getElementById("title").value,
      author: document.getElementById("author").value,
      pages: document.getElementById("pages").value,
      image: document.getElementById("image").value,
      read: false,
    };

    // Añadir a la biblioteca y al DOM
    library.push(newBook);
    addBookToLayout(newBook);

    // Reset y cerrar form
    form.reset();
    if (modal) modal.style.display = "none";
    else form.style.display = "none";
  });

  //Delegación de eventos para botones dentro del grid
  layout.addEventListener("click", (event) => {
    // Eliminar libro
    if (event.target.classList.contains("delete")) {
      event.target.closest(".book").remove();
      return;
    }

    // Cambiar estado Read/Unread
    if (event.target.classList.contains("book-status")) {
      const button = event.target;
      const isRead = button.textContent === "Unread";
      button.textContent = isRead ? "Read" : "Unread";
      button.classList.toggle("read", isRead);
    }
  });

  renderLibrary();
});

