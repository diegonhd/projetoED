import React from "react";
import Modal from "../Modal/Modal.jsx";
import OperationButton from "../OperationButton/OperationButton.jsx"
import OperationInput from "../OperationInput/OperationInput.jsx";
import "./DepositModal.css"

export default function DepositModal(props) {
    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <form className="deposit-container">
                <OperationInput text="R$ 0.00" label="Valor a depositar" isNumeric={true}/>
                <OperationButton>Depositar</OperationButton>
            </form>
        </Modal>
    )
}