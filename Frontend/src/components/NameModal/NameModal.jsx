import React, { useState } from "react";
import Modal from "../Modal/Modal.jsx";
import OperationButton from "../OperationButton/OperationButton.jsx"
import OperationInput from "../OperationInput/OperationInput.jsx";
import "./NameModal.css"

export default function NameModal(props) {
    const [inputValue, setInputValue] = useState("Cliente")

    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade} width="20vw" height="40vh">
            <form className="name-container" onSubmit={(event) => {
                event.preventDefault()
                props.setName(inputValue)
                props.setStade(false)
            }}>
                <OperationInput text="Seu nome" label="Qual é seu nome?" setValue={setInputValue}/>
                <OperationButton>Pronto</OperationButton>
            </form>
        </Modal>
    )
}