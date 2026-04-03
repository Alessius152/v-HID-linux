"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const http_1 = require("http");
const socket_io_1 = require("socket.io");
const constants_1 = require("./constants");
const ws_1 = require("./config/ws");
const path_1 = __importDefault(require("path"));
const app = (0, express_1.default)();
const httpServer = (0, http_1.createServer)(app);
const io = new socket_io_1.Server(httpServer, {
    cors: {
        origin: "*",
    }
});
(0, ws_1.startupWebSocketListeners)(io);
app.get('/hid', (req, res) => {
    res.sendFile(path_1.default.resolve(__dirname, './static/index.html'));
});
httpServer.listen(constants_1.SERVER_PORT, constants_1.SERVER_HOST, () => {
    console.log('server started');
});
//# sourceMappingURL=server.js.map