import React, { useEffect, useState } from "react";
import Modal from "../Modal/Modal.jsx";
import CardTransaction from "../CardTransaction/CardTransaction.jsx";
import "./DetailsModal.css"
import { getAllOperations } from "../../services/operation.js";

export default function DetailsModal(props) {
    const [allOperations, setAllOperations] = useState([])

    async function fecthAllOperations() {
        const op = await getAllOperations()
        setAllOperations(op)
    }

    useEffect(() => {
        fecthAllOperations()
    }, [props.update])

    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <div className="details-container">
                <h2>Histórico de Transações</h2>
                <div className="operations-list">
                    {allOperations.map((operation) => (
                        <div className="operation-item" key={operation.id} >
                            <CardTransaction 
                                setId={props.setId}
                                id={operation.id} 
                                value={operation.value} type={operation.type}
                                func={() => props.setOpenOperation(true)}
                            />
                        </div>
                    ))}
                </div>
            </div>
        </Modal>
    )
}