import React from "react";
import "./Balance.css"

export default function Balance() {
    return (
        <section className="balance-container">
            <h2>Olá, Cliente</h2>
            <p>Bem-vindo de volta</p>
            <p className="balance">Saldo: R$1.234,53</p>
        </section>
    )
}