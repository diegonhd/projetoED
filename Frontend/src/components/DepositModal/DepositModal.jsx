import React from "react";
import Modal from "../Modal/Modal.jsx";

export default function DepositModal(props) {
    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <p>Depósito</p>
        </Modal>
    )
}