import React from "react";
import "./OperationSelect.css"

export default function OperationSelect(props) {
    return (
        <div className="select-container">
            <label htmlFor="">{props.label}</label>
            <select className="select">
                <option value="MyBank">MyBank</option>
            </select>
        </div>
    )
}