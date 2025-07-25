import React from "react";
import OperationButton from "../OperationButton/OperationButton";
import "./Balance.css"

export default function Balance(props) {
    return (
        <section className="balance-container">
            <div>
                <h2>Olá, Cliente</h2>
                <p>Bem-vindo de volta</p>
                <p className="balance">Saldo: R$1.234,53</p>
            </div>
            <OperationButton func={props.setStatement} stade={props.statement}>
                Extrato
            </OperationButton>
        </section>
    )
}