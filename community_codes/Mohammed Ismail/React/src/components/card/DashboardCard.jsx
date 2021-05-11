import React from 'react';

export const DashboardCard = (props) => {

    const onClick = () => {
        if (props.onClick) {
            props.onClick();
        }
    }

    const icon = {
        backgroundImage: "url(" + "https://mohammed-ismail.co.za/offerZen/img/plant.png" + ")"
    }

    return (
        <div className={`card card-stats mb-4 mb-xl-0 ${props.onClick ? ' pointer' : ''}`} onClick={onClick}>
            <div className="card-body">
                <div className="row">
                    <div className="col">
                        <h5 className="card-title text-uppercase text-muted mb-0">{props.title}</h5>
                        <span className="h2 font-weight-bold mb-0">{props.value}<span style={{ color: "lightgrey" }}>{props.unit}</span></span>
                    </div>
                    <div className="col-auto">
                        <div className={`icon icon-shape ${props.iconColour} text-white rounded-circle shadow`}>
                            <i><img src="https://mohammed-ismail.co.za/offerZen/img/plant.png"></img></i>
                        </div>
                    </div>
                </div>
                {
                    (props.onClick || props.description) &&
                    <p className="mt-3 mb-0 text-muted text-sm">
                        {props.onClick && <span className="text-info mr-2"><i className="far fa-hand-point-up"></i></span>}
                        <span className="text-nowrap">{props.description}</span>
                    </p>
                }
            </div>
        </div>
    );
}