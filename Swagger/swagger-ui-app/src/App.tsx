import React from 'react';
import logo from './logo.svg';
import './App.css';
import SwaggerUI from "swagger-ui-react"
import "swagger-ui-react/swagger-ui.css"

function App() {
  return (
      <SwaggerUI tryItOutEnabled={false} url="/swagger/doc.json" />
  );
}

export default App;
