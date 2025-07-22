import React from "react";
import Modal from "../Modal/Modal.jsx";
import OperationButton from "../OperationButton/OperationButton.jsx"
import OperationInput from "../OperationInput/OperationInput.jsx";
import "./WithdrawalModal.css"

export default function WithdrawalModal(props) {
    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <form className="withdrawal-container">
                <OperationInput text="R$ 0.00" label="Valor a sacar"/>
                <OperationButton>Depositar</OperationButton>
            </form>
        </Modal>
    )
}