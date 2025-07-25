import React, { useState } from "react";
import { motion } from "framer-motion";
import OperationInput from "../OperationInput/OperationInput";
import OperationButton from "../OperationButton/OperationButton";
import "./Account.css"

export default function Account(props) {

    if (props.isOpen) {
        const [inputName, setInputName] = useState(props.name)
        const [inputCPF, setInputCPF] = useState(props.CPF)
        const [inputEmail, setInputEmail] = useState(props.email)

        return (
            <motion.section 
                className="account-container"
                initial={{ opacity: 0, transform: "translate3d(-50px, 0, -5px)"}}
                animate={{ opacity: 1, transform: "translate3d(0, 0, 0)"}}
                exit={{ opacity: 0, transform: "translate3d(-40px, 0, -5px)"}}
            >
                <h1>Minha conta</h1>
                <form className="infoAccount-container" onSubmit={(event) => {
                    event.preventDefault()
                    props.setName(inputName)
                    props.setCPF(inputCPF)
                    props.setEmail(inputEmail)
                }}>
                    <div className="account-input">
                        <label>Nome: </label>
                        <OperationInput width="200px" value={inputName} setValue={setInputName}/>
                    </div>
                    <div className="account-input">
                        <label>CPF: </label>
                        <OperationInput width="200px" value={inputCPF} setValue={setInputCPF} isNumeric={true}/>
                    </div>
                    <div className="account-input">
                        <label>Email: </label>
                        <OperationInput width="200px" value={inputEmail} setValue={setInputEmail}/>
                    </div>
                    <OperationButton>Salvar alteração</OperationButton>
                </form>
            </motion.section>
        )
    } else {
        return null
    }
}