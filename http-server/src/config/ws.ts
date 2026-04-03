import { Server } from "socket.io"

function startupWebSocketListeners(io: Server) {
    io.on('connection', (socket) => {
        console.log('connected', socket.id)

        socket.on('hid-interaction', (data)=>{
            console.log(data)
        })

        socket.on('disconnect', ()=>{
            console.log("disconnected", socket.id)
        })
    })
}

export {
    startupWebSocketListeners,
}
