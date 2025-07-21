import React from "react";
import Modal from "../Modal/Modal.jsx";
import "./DepositModal.css"

export default function DepositModal(props) {
    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <form className="deposit-container">
                <label>Valor a depositar</label>
                <input type="text" required placeholder="R$ 0.00"/>
                <button>Depositar</button>
            </form>
        </Modal>
    )
}