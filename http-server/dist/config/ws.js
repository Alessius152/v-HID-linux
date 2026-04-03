"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.startupWebSocketListeners = startupWebSocketListeners;
function startupWebSocketListeners(io) {
    io.on('connection', (socket) => {
        console.log('connected', socket.id);
        socket.on('new-hid-interaction', (data) => {
            console.log('data', data);
        });
        socket.on('disconnect', () => {
            console.log('disconnected', socket.id);
        });
    });
}
//# sourceMappingURL=ws.js.map