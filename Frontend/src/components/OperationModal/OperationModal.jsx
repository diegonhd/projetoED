import React, { useEffect, useState } from "react";
import Modal from "../Modal/Modal.jsx";
import "./OperationModal.css"
import { getOperationById } from "../../services/operation.js";

export default function OperationModal(props) {
    const [operation, setOperation] = useState()

    async function fetchOperationById() {
        const response = await getOperationById(props.id)
        setOperation(response)
    }

    useEffect(() => {
        if (props.isOpen && props.id !== undefined && props.id !== null) {
            fetchOperationById()
        }
    }, [props.isOpen, props.id])

    if (!props.isOpen || !operation) return null;

    return (
        <Modal isOpen={props.isOpen} setStade={props.setStade}>
            <p>{props.isOpen ? operation.value : null}</p>
        </Modal>
    )
}