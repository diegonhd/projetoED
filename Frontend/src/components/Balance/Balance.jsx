import React, { useState, useEffect } from "react";
import OperationButton from "../OperationButton/OperationButton.jsx";
import NameModal from "../NameModal/NameModal.jsx";
import "./Balance.css"
import { getSaldo } from "../../services/operation.js";

export default function Balance(props) {
    const [openNameModal, setOpenNameModal] = useState(false)
    const [saldo, setSaldo] = useState()

    async function fecthSaldo() {
        const response = await getSaldo()
        setSaldo(response.saldo)
    }

    useEffect(() => {setOpenNameModal(true)}, [])

    useEffect(() => {
        fecthSaldo()
    }, [props.update])

    return (
        <section className="balance-container">
            <div>
                <h2>Olá, {props.name}</h2>
                <p>Bem-vindo de volta</p>
                <p className="balance">Saldo: R${new Intl.NumberFormat('pt-BR', {
                                                    minimumFractionDigits: 2,
                                                    maximumFractionDigits: 2
                                                }).format(parseFloat(saldo))}</p>
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