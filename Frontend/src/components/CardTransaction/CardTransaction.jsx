import React from "react"
import "./CardTransaction.css"

export default function CardTransaction(props) {
    return (
        <div 
            className="card-container"
            style={{backgroundColor: props.type == "DEPOSITO" ? "#E6F6E6" : "#f6e6e6"}}
        >
            <p className="value">
                {props.type == "DEPOSITO" ? "+" : "-"}R${new Intl.NumberFormat('pt-BR', {
                                                            minimumFractionDigits: 2,
                                                            maximumFractionDigits: 2
                                                        }).format(parseFloat(props.value))}
            </p>
            <p className="type">{props.type}</p>
        </div>
    )
}
