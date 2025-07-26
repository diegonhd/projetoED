import axios from "axios"

const apiOperations = axios.create({baseURL: "http://127.0.0.1:3000/operation"})

async function getAllOperations() {
    const response = await apiOperations.get("/all")

    return response.data
}

async function getFiveOperations() {
    const response = await apiOperations.get("/lasts")

    return response.data
}

async function getOperationById(id) {
    const response = await apiOperations.get(`/${id}`)

    return response.data
}

async function getSaldo() {
    const response = await apiOperations.get("/saldo")

    return response.data
}

async function createDeposit(newOperation) {
    const response = await apiOperations.post("/deposit", newOperation)

    return response.data
}

async function createWithdrawal(newOperation) {
    const response = await apiOperations.post("/withdrawal", newOperation)

    return response.data
}

async function createTransfer(newOperation) {
    const response = await apiOperations.post("/transfer", newOperation)

    return response.data
}

export {
    getAllOperations,
    getFiveOperations,
    getOperationById,
    getSaldo,
    createDeposit,
    createWithdrawal,
    createTransfer
}