import React from "react";
import { motion } from "framer-motion";
import "./Statement.css"

export default function Statement(props) {
    if (props.isOpen) {
        return (
            <motion.section 
                className="statement-container"
                initial={{ opacity: 0, transform: "translate3d(-50px, 0, -5px)"}}
                animate={{ opacity: 1, transform: "translate3d(0, 0, 0)"}}
                exit={{ opacity: 0, transform: "translate3d(-40px, 0, -5px)"}}
            >
                <h1>Extrato Bancário</h1>
            </motion.section>
        )
    } else {
        return null
    }
}