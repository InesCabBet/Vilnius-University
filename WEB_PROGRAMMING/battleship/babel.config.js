// babel.config.js
module.exports = {
  presets: [['@babel/preset-env', { targets: { node: 'current' } }]],
};

// package.json additions (merge with existing file)
// Add this to your scripts section:
// "scripts": {
//   "test": "jest",
//   "test:watch": "jest --watch"
// }