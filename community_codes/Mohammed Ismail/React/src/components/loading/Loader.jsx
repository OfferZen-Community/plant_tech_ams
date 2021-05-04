import React from 'react';
import './_Loading.scss';

export const Loader = (props) => {
    return (
        <>
            <div className="full-page-loader initial intro-background"></div>
            <div className="full-page-loader initial">
                <div className="cssload-container">
                    <ul className="cssload-flex-container">
                        <li style={{ listStyleType: "none" }}>
                            <img src="https://mohammed-ismail.co.za/offerZen/img/brand/loading.svg" alt="loading-animation" />
                            <h1 className="largeHeading font-weight-bold">{props.title ? props.title : 'Loading'}</h1>
                        </li>
                    </ul>
                </div>
            </div>
        </>
    );
}