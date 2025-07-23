import React from "react";
import Modal from "../Modal/Modal.jsx";
import OperationButton from "../OperationButton/OperationButton.jsx"
import OperationInput from "../OperationInput/OperationInput.jsx";
import OperationSelect from "../OperationSelect/OperationSelect.jsx";
import "./TransferModal.css"

export default function TransferModal(props) {
    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <form action="" className="transfer-container">
                <div className="grid">
                    <div className="first-row">
                        <OperationInput text="R$ 0.00" label="Valor" isNumeric={true}/>
                        <OperationSelect label="Instituição"/>
                    </div>
                    <OperationInput text="Nome da pessoa" label="Pagar para" width="220px"/>
                </div>
                <OperationButton>Transferir</OperationButton>
            </form>
        </Modal>
    )
}