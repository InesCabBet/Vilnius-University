import './style.css';

const API_KEY = 'af5fa807e250488a914201436252911';
const API_URL = 'https://api.weatherapi.com/v1/forecast.json';

// Get DOM element
const content = document.getElementById('content');

// Initialize app
function init() {
    renderUI();
    setupEventListeners();
}

// Render initial UI
function renderUI() {
    content.innerHTML = `
        <div class="header">
            <h1>⛅ Weather App</h1>
            <p>Search weather for any city in the world</p>
        </div>

        <div class="search-container">
            <input type="text" id="cityInput" placeholder="Enter a city name...">
            <button id="searchBtn">Search</button>
        </div>

        <div id="weatherDisplay"></div>
    `;
}

// Setup event listeners
function setupEventListeners() {
    const searchBtn = document.getElementById('searchBtn');
    const cityInput = document.getElementById('cityInput');

    searchBtn.addEventListener('click', handleSearch);
    cityInput.addEventListener('keypress', (e) => {
        if (e.key === 'Enter') {
            handleSearch();
        }
    });
}

// Handle search
async function handleSearch() {
    const cityInput = document.getElementById('cityInput');
    const city = cityInput.value.trim();

    if (!city) return;

    showLoading();

    try {
        const weather = await fetchWeather(city);
        displayWeather(weather);
    } catch (error) {
        showError(error.message);
    }
}

// Fetch weather data
async function fetchWeather(city) {
    const response = await fetch(`${API_URL}?key=${API_KEY}&q=${city}&days=3&aqi=no`);
    
    if (!response.ok) {
        throw new Error('City not found');
    }

    return await response.json();
}

// Show loading state
function showLoading() {
    const weatherDisplay = document.getElementById('weatherDisplay');
    weatherDisplay.innerHTML = `
        <div class="loading">
            <div class="spinner"></div>
            <p>Loading...</p>
        </div>
    `;
}

// Show error message
function showError(message) {
    const weatherDisplay = document.getElementById('weatherDisplay');
    weatherDisplay.innerHTML = `
        <div class="error">
            <p>${message}</p>
        </div>
    `;
}

// Display weather data
function displayWeather(data) {
    const weatherDisplay = document.getElementById('weatherDisplay');
    const { location, current, forecast } = data;

    weatherDisplay.innerHTML = `
        <div class="weather-container">
            <div class="current-weather">
                <div class="location-info">
                    <div>
                        <h2>📍 ${location.name}</h2>
                        <p class="country">${location.country}</p>
                        <p class="local-time">${location.localtime}</p>
                    </div>
                    <img src="https:${current.condition.icon}" alt="${current.condition.text}" class="weather-icon">
                </div>

                <div class="temperature-display">
                    <div class="temperature">${Math.round(current.temp_c)}°C</div>
                    <p class="condition">${current.condition.text}</p>
                    <p class="feels-like">Feels like: ${Math.round(current.feelslike_c)}°C</p>
                </div>

                <div class="weather-details">
                    <div class="detail-card">
                        <p class="label">💨 Wind</p>
                        <p class="value">${current.wind_kph} km/h</p>
                    </div>
                    <div class="detail-card">
                        <p class="label">💧 Humidity</p>
                        <p class="value">${current.humidity}%</p>
                    </div>
                    <div class="detail-card">
                        <p class="label">👁️ Visibility</p>
                        <p class="value">${current.vis_km} km</p>
                    </div>
                    <div class="detail-card">
                        <p class="label">🌡️ Pressure</p>
                        <p class="value">${current.pressure_mb} mb</p>
                    </div>
                </div>

                <div class="sun-times">
                    <div class="sun-card">
                        <span style="font-size: 2rem;">🌅</span>
                        <div>
                            <p class="label">Sunrise</p>
                            <p class="value">${forecast.forecastday[0].astro.sunrise}</p>
                        </div>
                    </div>
                    <div class="sun-card sunset">
                        <span style="font-size: 2rem;">🌇</span>
                        <div>
                            <p class="label">Sunset</p>
                            <p class="value">${forecast.forecastday[0].astro.sunset}</p>
                        </div>
                    </div>
                </div>
            </div>
            </div>
        </div>
    `;
}

// Format date
function formatDate(dateString) {
    const date = new Date(dateString);
    const options = { weekday: 'short', day: 'numeric', month: 'short' };
    return date.toLocaleDateString('en-US', options);
}

// Start the app
init();