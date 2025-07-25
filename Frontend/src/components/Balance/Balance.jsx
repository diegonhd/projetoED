import React, { useState, useEffect } from "react";
import OperationButton from "../OperationButton/OperationButton.jsx";
import NameModal from "../NameModal/NameModal.jsx";
import "./Balance.css"

export default function Balance(props) {
    const [openNameModal, setOpenNameModal] = useState(false)

    useEffect(() => {setOpenNameModal(true)}, [])

    return (
        <section className="balance-container">
            <div>
                <h2>Olá, {props.name}</h2>
                <p>Bem-vindo de volta</p>
                <p className="balance">Saldo: R$1.234,53</p>
            </div>
            <div className="buttons-balance">
                
                <OperationButton func={() => {
                    props.setStatement(false)
                    props.setAccount(!props.account)
                }}>Minha conta</OperationButton>

                <OperationButton func={() => {
                    props.setStatement(!props.statement)
                    props.setAccount(false)
                }}>Extrato</OperationButton>

            </div>
            <NameModal isOpen={openNameModal} setStade={setOpenNameModal} setName={props.setName}/>
        </section>
    )
}