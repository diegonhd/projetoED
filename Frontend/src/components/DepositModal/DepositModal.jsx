import React, { useState } from "react";
import Modal from "../Modal/Modal.jsx";
import OperationButton from "../OperationButton/OperationButton.jsx"
import OperationInput from "../OperationInput/OperationInput.jsx";
import "./DepositModal.css"
import { createDeposit } from "../../services/operation.js";

export default function DepositModal(props) {
    const [value, setValue] = useState()

    async function postDeposit(newOperation) {
        const response = await createDeposit(newOperation)
        console.log(response)
    }

    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <form className="deposit-container" onSubmit={(event) => {
                event.preventDefault()
                const newOperation = {value: parseInt(value), date: new Date().toLocaleString("PT-br")}
                postDeposit(newOperation)
                props.setUpdate(Math.random)
                setValue("")
                props.setStade(false)
            }}>
                <OperationInput text="R$ 0.00" label="Valor a depositar" isNumeric={true} value={value} setValue={setValue}/>
                <OperationButton>Depositar</OperationButton>
            </form>
        </Modal>
    )
}