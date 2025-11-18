import "./style.css";
import { loadHome } from "./home.js";
import { loadMenu } from "./menu.js";
import { loadContact } from "./contact.js";

// Initial load
loadHome();

// Tab switching
document.getElementById("home").addEventListener("click", loadHome);
document.getElementById("menu").addEventListener("click", loadMenu);
document.getElementById("contact").addEventListener("click", loadContact);