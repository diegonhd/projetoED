import React from "react";
import Modal from "../Modal/Modal.jsx";

export default function TransferModal(props) {
    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <p>Transferência</p>
        </Modal>
    )
}