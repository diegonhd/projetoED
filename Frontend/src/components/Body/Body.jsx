import React, { useState } from "react"
import Balance from "../Balance/Balance.jsx"
import Operation from "../Operation/Operation.jsx"
import Statement from "../Statement/Statement.jsx"
import Account from "../Account/Account.jsx"
import DetailsModal from "../DetailsModal/DetailsModal"
import OperationModal from "../OperationModal/OperationModal.jsx"
import "./Body.css"

export default function Body() {
    const [name, setName] = useState("Cliente")
    const [CPF, setCPF] = useState()
    const [email, setEmail] = useState()
    const [id, setId] = useState()

    const [openStatement, setOpenStatement] = useState(false)
    const [openAccount, setOpenAccount] = useState(false)

    const [update, setUpdate] = useState(0)

    const [openDetails, setOpenDetails] = useState(false)
    const [openOperation, setOpenOperation] = useState(false)

    return (
        <section className="body-container">
            <div className="info-container">
                <div>
                    <Balance 
                        statement={openStatement} setStatement={setOpenStatement}
                        account={openAccount} setAccount={setOpenAccount}
                        name={name} setName={setName}
                        update={update}
                    />
                    <Operation setUpdate={setUpdate}/>
                </div>
                <Statement 
                    isOpen={openStatement} update={update}
                    setOpenDetails={setOpenDetails}
                    setOpenOperation={setOpenOperation}
                    setId={setId}
                />
                <Account isOpen={openAccount} 
                    name={name} setName={setName}
                    CPF={CPF} setCPF={setCPF}
                    email={email} setEmail={setEmail}
                />
                <DetailsModal 
                    isOpen={openDetails} setStade={setOpenDetails} 
                    setOpenOperation={setOpenOperation} update={update}
                    setId={setId}
                />
                <OperationModal isOpen={openOperation} setStade={setOpenOperation} id={id}/>
            </div>
        </section>
    )
}