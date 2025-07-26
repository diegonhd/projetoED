import React, { useState } from "react";
import Modal from "../Modal/Modal.jsx";
import OperationButton from "../OperationButton/OperationButton.jsx"
import OperationInput from "../OperationInput/OperationInput.jsx";
import OperationSelect from "../OperationSelect/OperationSelect.jsx";
import "./TransferModal.css"
import { createTransfer } from "../../services/operation.js";

export default function TransferModal(props) {
    const [value, setValue] = useState()
    const [destino, setDestino] = useState()

    async function postTransfer(newOperation) {
        const response = await createTransfer(newOperation)
        console.log(response)
    }

    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <form action="" className="transfer-container" onSubmit={(event) => {
                event.preventDefault()
                const newOperation = {value: parseInt(value), date: new Date().toLocaleString("PT-br"), destino: destino}
                postTransfer(newOperation)
                props.setUpdate(Math.random)
                setValue("")
                setDestino("")
                props.setStade(false)
            }}>
                <div className="grid">
                    <div className="first-row">
                        <OperationInput text="R$ 0.00" label="Valor" isNumeric={true} value={value} setValue={setValue}/>
                        <OperationSelect label="Instituição"/>
                    </div>
                    <OperationInput text="Nome da pessoa" label="Pagar para" width="220px" value={destino} setValue={setDestino}/>
                </div>
                <OperationButton>Transferir</OperationButton>
            </form>
        </Modal>
    )
}