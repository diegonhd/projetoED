import React, { useState } from "react"
import Balance from "../Balance/Balance.jsx"
import Operation from "../Operation/Operation.jsx"
import Statement from "../Statement/Statement.jsx"
import Account from "../Account/Account.jsx"
import "./Body.css"

export default function Body() {
    const [name, setName] = useState("Cliente")
    const [CPF, setCPF] = useState()
    const [email, setEmail] = useState()

    const [openStatement, setOpenStatement] = useState(false)
    const [openAccount, setOpenAccount] = useState(false)

    return (
        <section className="body-container">
            <div className="info-container">
                <div>
                    <Balance 
                        statement={openStatement} setStatement={setOpenStatement}
                        account={openAccount} setAccount={setOpenAccount}
                        name={name} setName={setName}
                    />
                    <Operation />
                </div>
                <Statement isOpen={openStatement}/>
                <Account isOpen={openAccount} 
                    name={name} setName={setName}
                    CPF={CPF} setCPF={setCPF}
                    email={email} setEmail={setEmail}
                />
            </div>
        </section>
    )
}