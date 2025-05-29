const express = require('express');
const httpProxy = require('http-proxy');

const app = express();
const proxy = httpProxy.createProxyServer({});

// Route all requests to the target HTTPS server
app.all('*', (req, res) => {
    console.log(`Proxying request: ${req.url}`);
    proxy.web(req, res, {
        target: 'https://localhost:8444', 
        secure: false
    });
});

// Handle proxy errors
proxy.on('error', (err, req, res) => {
    console.error('Proxy error:', err);
    res.status(500).send('Proxy error occurred');
});

const PORT = 8081;
app.listen(PORT, () => {
    console.log(`SSH Tunnel Proxy running at http://localhost:${PORT}`);
});
