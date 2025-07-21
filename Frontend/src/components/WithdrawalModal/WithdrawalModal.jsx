import React from "react";
import Modal from "../Modal/Modal.jsx";

export default function WithdrawalModal(props) {
    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <p>Saque</p>
        </Modal>
    )
}