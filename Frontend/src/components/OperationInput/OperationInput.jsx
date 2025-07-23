import React from "react";
import "./OperationInput.css"

export default function OperationInput(props) {
    return (
        <div className="input-container">
            <label>{props.label}</label>
            <input 
                type="text" 
                className="input" 
                required 
                placeholder={props.text} 
                value={props.value}
                style={{width: props.width}}
                onKeyDown={props.isNumeric ? (event) => {
                    const allowed = ["Backspace", "ArrowLeft", "ArrowRight", "Tab", "Delete"]

                    if (!/[0-9]/.test(event.key) && !allowed.includes(event.key)) {
                        event.preventDefault()
                    }
                } : null}
            />
        </div>
    )
}