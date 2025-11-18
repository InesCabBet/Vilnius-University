import restaurantImage from './restaurant.jpg';

export function loadHome() {
    const content = document.getElementById('content');
    content.innerHTML = '';

    const headline = document.createElement("h1");
    headline.textContent = "Welcome to Odin Restaurant";

    const description = document.createElement("p");
    description.textContent = "The finest dishes cooked by finest chefs, for our finest customers";

    const restaurantImg = document.createElement("img");
    restaurantImg.src = restaurantImage;
    restaurantImg.alt = "Beautiful restaurant interior";
    restaurantImg.style.maxWidth = "100%";
    restaurantImg.style.height = "auto";
    restaurantImg.style.borderRadius = '12px';
    restaurantImg.style.marginTop = '2rem';

    content.appendChild(headline);
    content.appendChild(description);
    content.appendChild(restaurantImg);

}