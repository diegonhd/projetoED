import React, { useState } from "react";
import Modal from "../Modal/Modal.jsx";
import OperationButton from "../OperationButton/OperationButton.jsx"
import OperationInput from "../OperationInput/OperationInput.jsx";
import "./WithdrawalModal.css"
import { createWithdrawal } from "../../services/operation.js";

export default function WithdrawalModal(props) {
    const [value, setValue] = useState()

    async function postWithdrawal(newOperation) {
        const response = await createWithdrawal(newOperation)
        console.log(response)
    }

    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <form className="withdrawal-container" onSubmit={(event) => {
                event.preventDefault()
                const newOperation = {value: parseInt(value), date: new Date().toLocaleString("PT-br")}
                postWithdrawal(newOperation)
                props.setUpdate(Math.random)
                setValue("")
                props.setStade(false)
            }}>
                <OperationInput text="R$ 0.00" label="Valor a sacar" isNumeric={true} value={value} setValue={setValue}/>
                <OperationButton>Sacar</OperationButton>
            </form>
        </Modal>
    )
}