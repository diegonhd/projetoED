import axios from "axios"

const apiOperations = axios.create({baseURL: "http://127.0.0.1:3000/operation"})

async function getFiveOperations() {
    const response = await apiOperations.get("/lasts")

    return response.data
}

export {
    getFiveOperations
}