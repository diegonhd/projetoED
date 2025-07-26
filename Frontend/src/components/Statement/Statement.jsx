import React, { useEffect, useState } from "react"
import { motion } from "framer-motion"
import CardTransaction from "../CardTransaction/CardTransaction"
import OperationButton from "../OperationButton/OperationButton"
import "./Statement.css"
import { getFiveOperations } from "../../services/operation"

export default function Statement(props) {
    const [operations, setOperations] = useState([])

    async function fecthFiveOperations() {
        const op = await getFiveOperations()
        setOperations(op)
    }

    useEffect(() => {
        fecthFiveOperations()
    }, [props.update])

    if (props.isOpen) {
        return (
            <motion.section 
                className="statement-container"
                initial={{ opacity: 0, transform: "translate3d(-50px, 0, -5px)"}}
                animate={{ opacity: 1, transform: "translate3d(0, 0, 0)"}}
                exit={{ opacity: 0, transform: "translate3d(-40px, 0, -5px)"}}
            >
                <h1>Extrato Bancário</h1>
                <div className="statement-cards">
                    {operations.map((operation) => (
                        <CardTransaction 
                            key={operation.id} 
                            setId={props.setId}
                            id={operation.id} value={operation.value} type={operation.type}
                            func={() => props.setOpenOperation(true)}
                        />
                    ))}
                </div>
                <div className="operation-btn">
                    <OperationButton func={() => {props.setOpenDetails(true)}}>Detalhes</OperationButton>
                </div>
            </motion.section>
        )
    } else {
        return null
    }
}