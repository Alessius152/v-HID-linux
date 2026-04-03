import express from 'express'
import { createServer } from 'http'
import { Server } from 'socket.io'
import { SERVER_HOST, SERVER_PORT } from './constants'
import { startupWebSocketListeners } from './config/ws'
import path from 'path'

const app = express()

const httpServer = createServer(app)

const io = new Server(httpServer, {
    cors: {
        origin: "*",
    }
})

app.use(express.static(path.resolve(__dirname, './static')))

startupWebSocketListeners(io)

app.get('/hid', (req, res)=>{

    res.sendFile(path.resolve(__dirname, './static/vhid.html'))

})

httpServer.listen(SERVER_PORT, SERVER_HOST, () => {
    console.log('server started')
})