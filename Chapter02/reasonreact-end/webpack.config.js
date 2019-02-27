const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");

const isProd = process.env.NODE_ENV === "production";

module.exports = {
  entry: "./src/Index.bs.js",
  mode: isProd ? "production" : "development",
  output: {
    path: path.join(__dirname, "build/"),
    filename: "Index.js"
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: "./src/index.html"
    })
  ]
};
